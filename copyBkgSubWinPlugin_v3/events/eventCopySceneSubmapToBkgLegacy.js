export const id = "EVENT_COPY_BKG_SUBMAP_TO_BKG_LEGACY";
export const name = "Copy scene submap to background (GBS 3)";
export const groups = ["EVENT_GROUP_SCREEN"];

export const autoLabel = (fetchArg) => {
  return `Copy scene submap to background (GBS 3)`;
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
    key: `source_x`,
    label: "Source X",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: `source_y`,
    label: "Source Y",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: `dest_x`,
    label: "Destination X",
    type: "number",
    width: "50%",
    defaultValue: 0,
  },
  {
    key: `dest_y`,
    label: "Destination Y",
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
];

export const compile = (input, helpers) => {
  const { options, _callNative, _stackPushConst, _stackPop, _addComment } = helpers;
  
  const { scenes } = options;
  const scene = scenes.find((s) => s.id === input.sceneId);
  if (!scene) {
    return;
  }
    
  _addComment("Copy scene submap to background (GBS 3)");
  
  _stackPushConst(`_${scene.symbol}`);
  _stackPushConst(`___bank_${scene.symbol}`); 
  _stackPushConst(input.h);
  _stackPushConst(input.w);
  _stackPushConst(input.dest_y);
  _stackPushConst(input.dest_x);
  _stackPushConst(input.source_y);
  _stackPushConst(input.source_x);
  		 
  _callNative("copy_background_submap_to_background");
  _stackPop(8);  
  
};
