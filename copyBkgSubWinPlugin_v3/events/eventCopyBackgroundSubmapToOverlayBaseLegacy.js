export const id = "EVENT_COPY_BKG_SUBMAP_TO_WIN_BASE_LEGACY";
export const name = "Copy scene submap to overlay with tile offset (GBS 3)";
export const groups = ["EVENT_GROUP_SCREEN"];

export const autoLabel = (fetchArg) => {
  return `Copy scene submap to overlay with tile offset (GBS 3)`;
};

export const fields = [
  {
    key: "sceneId",
    label: "Scene",
    type: "scene",
	width: "100%",
    defaultValue: "LAST_SCENE",
  },
  {
    key: `bkg_x`,
    label: "Background X",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: `bkg_y`,
    label: "Background Y",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: `win_x`,
    label: "Overlay X",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: `win_y`,
    label: "Overlay Y",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: "w",
    label: "width",
    description: "width",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: "h",
    label: "height",
    description: "height",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: "tile_offset",
    label: "tile idx offset",
    description: "height",
    type: "number",
    width: "100%",
    defaultValue: 0,
  },
];

export const compile = (input, helpers) => {
  const { options, _callNative, _stackPushConst, _stackPop, _addComment } = helpers;
  
  const { scenes } = options;
  const scene = scenes.find((s) => s.id === input.sceneId);
  if (!scene) {
    return;
  }
     
  _addComment("Copy scene submap to overlay with tile offset (GBS 3)");
  
  _stackPushConst(`_${scene.symbol}`);
  _stackPushConst(`___bank_${scene.symbol}`); 
  _stackPushConst(input.tile_offset); 
  _stackPushConst((input.h << 8) | input.w); 
  _stackPushConst((input.win_y << 8) | input.win_x); 
  _stackPushConst((input.bkg_y << 8) | input.bkg_x); 
  		
  _callNative("copy_background_submap_to_overlay_base");
  _stackPop(6);  
  
};
